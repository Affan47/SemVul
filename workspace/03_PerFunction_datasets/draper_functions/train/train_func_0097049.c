browseProtein()
{

    FileDialog fd;
    aaMatrixPath = fd.getOpenFileName(this, tr("Find Protein Matrix"));

    string path = aaMatrixPath.toStdString();

    if(path != "")
    {
        int lenOfString = path.length();

        char* userFile = new char[lenOfString + 1];
        strcpy(userFile, path.c_str());

        if (clustalw::subMatrix->getUserMatFromFile(userFile, clustalw::Protein,
                                                    clustalw::MultipleAlign))
        {
            aaMatrixFile = string(userFile);
            proteinMatLoaded = true;
            userProteinMatrix->setText(aaMatrixFile.c_str());
            radioSetUsingUserProtein();
        }
        else
        {
            aaMatrixFile = "";
            proteinMatLoaded = false;
            userProteinMatrix->setText(aaMatrixFile.c_str());
            setInitialProteinMat();
        }
        delete []userFile;
    }
    else
    {
        if(!proteinMatLoaded)
        {
            setInitialProteinMat();
        }
    }
}
