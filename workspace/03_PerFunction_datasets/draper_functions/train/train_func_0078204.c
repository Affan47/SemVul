main(int argc, char *argv[])
{

    if(argc<2)
	{cout<< "\n randomsphere v."<<version<< "\n\n";
    cout<< " Usage:\n randomsphere <filename> \n";
    cout<<" To create a new source file: randomsphere -n \n\n";}

    if(argc>=2)
	{   if(strcmp(argv[1],"-n")==0)
            {createNew();}
        else
           {operate(argv[1]);}

    return 0;
    }
}
