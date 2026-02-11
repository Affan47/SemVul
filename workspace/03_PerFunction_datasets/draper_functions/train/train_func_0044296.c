promptInputFile(QFile& infile) {
    QString filename;
    while (1) {
        cout << "Name of the file to be read:  ";
        cout.flush();
        filename = cin.readLine();
        infile.setFileName(filename);
        bool fileExists = infile.open(QIODevice::ReadOnly);
        if (fileExists)
            break;
        cout << "File does not exist ... Please try again. \n";
        cout.flush();
        infile.reset();
    }
    cout << filename << " open for reading ...\n";
    cout.flush();
}
