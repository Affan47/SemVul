printInFormat(vector<short>& temp, char* name)
{
    char nameOfFile[30];
    strcpy(nameOfFile, name);
    strcat(nameOfFile, ".out");

    ofstream outfile(nameOfFile);

    if(!outfile)
        cerr<<"oops failed to open !!!\n";

    outfile<<"short "<<name<<"[]{\n";

    int numOnCurrentLine = 1;
    int soFar = 0;
    for(int i = 0; i < (int)temp.size(); i++)
    {
        if(soFar == numOnCurrentLine)
        {
            outfile<<"\n";
            soFar = 0;
            numOnCurrentLine++;
        }
        if((temp[i] > 9) || (temp[i] < 0))
        {
            outfile <<" "<< temp[i]<<",";
        }
        else
        {
            outfile <<"  "<< temp[i]<<",";
        }


        soFar++;

        if((i + 1) == (int)temp.size() - 1)
        {

            if((temp[i+1] > 9) || (temp[i+1] < 0))
            {
                outfile <<" "<< temp[i + 1]<<"};\n";
            }
            else
            {
                outfile <<"  "<< temp[i + 1]<<"};\n";
            }
            break;
        }
    }

    ofstream outfile2("temp.out");
    for(int i = 0; i < (int)temp.size(); i++)
    {
        outfile2 << temp[i] << " ";
    }
}
