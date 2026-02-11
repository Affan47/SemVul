openOutputFile(auto_ptr<ofstream>& outFile, string prompt,
                                       string path, string fileExtension)
{
    string temp;
    string _fileName;
    string message;
    _fileName = path + fileExtension;

    if(_fileName.compare(userParameters->getSeqName()) == 0)
    {
        cout << "Output file name is the same as input file.\n";
        if (userParameters->getMenuFlag())
        {
            message = "\n\nEnter new name to avoid overwriting  [" + _fileName + "]";

            utilityObject->getStr(message, temp);
            if(temp != "")
            {
                _fileName = temp;
            }
        }
    }
    else if (userParameters->getMenuFlag())
    {

        message = prompt + " [" + _fileName + "]";
        utilityObject->getStr(message, temp);
        if(temp != "")
        {
            _fileName = temp;
        }
    }

    outFile.reset(new ofstream(_fileName.c_str(), ofstream::trunc));
    if(!outFile->is_open())
    {
        utilityObject->error("Cannot open output file [%s]\n", _fileName.c_str());
        return "";
    }
    return _fileName;
}
