importFiles(MainWindow *mainWindow, QStringList files)
{
    QStringList videos, workouts;
    MediaHelper helper;


    foreach(QString file, files) {


        if (!QFile(file).exists()) continue;


        if (helper.isMedia(file)) videos << file;


        if (ErgFile::isWorkout(file)) {
            int mode;
            ErgFile *p = new ErgFile(file, mode, mainWindow);
            if (p->isValid()) workouts << file;
            delete p;
        }
    }


    if (!videos.count() && !workouts.count()) {

        QMessageBox::warning(NULL, tr("Import Videos and Workouts"),
            "No supported videos or workouts were found to import");

        return;
    }


    if (videos.count()<=1 && workouts.count() <= 1) {

        trainDB->startLUW();

        Library *l = Library::findLibrary("Media Library");


        if (videos.count()) {

            if (l->refs.contains(videos[0])) {


            } else {
                l->refs.append(videos[0]);
            }

            trainDB->importVideo(videos[0]);
        }

        QString target;
        if (workouts.count()) {

            QFile source(workouts[0]);


            QString workoutDir = appsettings->value(NULL, GC_WORKOUTDIR).toString();
            if (workoutDir == "") {
                QDir root = mainWindow->home;
                root.cdUp();
                workoutDir = root.absolutePath();
            }


            target = workoutDir + "/" + QFileInfo(source).fileName();

            if (!source.copy(target)) {

                QMessageBox::warning(NULL, tr("Copy Workout Failed"),
                    QString("%1 already exists in workout library").arg(QFileInfo(target).fileName()));
            }


            int mode;
            ErgFile file(target, mode, mainWindow);
            trainDB->importWorkout(target, &file);

        }

        trainDB->endLUW();


        LibraryParser::serialize(mainWindow->home);


        if (videos.count()) mainWindow->notifySelectVideo(videos[0]);
        if (workouts.count()) mainWindow->notifySelectWorkout(target);

    } else {


        WorkoutImportDialog *p = new WorkoutImportDialog(mainWindow, files);
        p->exec();
    }
}
