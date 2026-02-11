main(int argc, char* argv[]) {


    if ( (argc == 1) ) return Help(argc, argv);


    if ( IsHelp(argv[1]) ) return Help(argc, argv);


    if ( IsVersion(argv[1]) ) return Version();


    AbstractTool* tool = CreateTool( argv[1] );
    if ( tool ) return tool->Run(argc, argv);


    return Help(argc, argv);
}
