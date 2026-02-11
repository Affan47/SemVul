alignProfilesFromGuideTrees()
{
    int nSeqs = alignPtr->getNumSeqs();
    if(nSeqs == 0)
    {
        QMessageBox::information(this, "", "No sequences loaded", QMessageBox::Ok);
        return;
    }
    if(clustalw::userParameters->getProfile1Empty())
    {
        QMessageBox::information(this, "", "Profile 1 empty", QMessageBox::Ok);
        return;
    }
    if(clustalw::userParameters->getProfile2Empty())
    {
        QMessageBox::information(this, "", "Profile 2 empty", QMessageBox::Ok);
        return;
    }
    FileNameDialogType type = AlignProf2ToProf1WithTree;
    AlignType alignType = Profile;
    AlignOutputFileNames namesDialog(sequenceFileName, type, alignType, profile2FileName);
    int code = namesDialog.exec();

    if(code == QDialog::Accepted)
    {
        clustalw::AlignmentFileNames names = namesDialog.getNames();
        string phylipName1 = names.treeFile;
        string phylipName2 = names.profile2TreeFile;
        clustalObj->QTSetFileNamesForOutput(names);


        int prof1First = alignmentViewer->getFirstSeq();
        int prof1Last  = alignmentViewer->getLastSeq();
        int prof2First = profile2Viewer->getFirstSeq();
        int prof2Last  = profile2Viewer->getLastSeq();

        alignmentViewer->updateView(0, 0);
        profile2Viewer->updateView(0, 0);


        if(phylipName1 != "")
        {
            clustalw::userParameters->setUseTree1File(true);
        }
        else
        {
            clustalw::userParameters->setUseTree1File(false);
        }
        if(phylipName2 != "")
        {
            clustalw::userParameters->setUseTree2File(true);
        }
        else
        {
            clustalw::userParameters->setUseTree2File(false);
        }
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        clustalObj->profileAlign(&phylipName1, &phylipName2);

        if(alignPtr->getNumSeqs() > 0)
        {


            alignmentViewer->updateView(prof1First, prof1Last);
            profile2Viewer->updateView(prof2First, prof2Last);

            if(showLowScoreSegments == true)
            {
                calculateLowScoreAlign();
            }
        }
        searchBeginSeq = 0;
        searchBeginRes = 1;
        QApplication::restoreOverrideCursor();
    }
    alignmentViewer->updateView();
}
