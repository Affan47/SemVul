formatOptionsMenu()
{

    while (true)
    {
        lin1 = "";
        cout<<"\n\n\n";
        cout<<" ********* Format of Alignment Output *********\n\n\n";
        cout<<"     F. Toggle FASTA format output       =  "
            << ((!userParameters->getOutputFasta()) ? "OFF" : "ON") <<"\n\n";
        cout<<"     1. Toggle CLUSTAL format output     =  "
            << ((!userParameters->getOutputClustal()) ? "OFF" : "ON") <<"\n";
        cout<<"     2. Toggle NBRF/PIR format output    =  "
            << ((!userParameters->getOutputNbrf()) ? "OFF" : "ON") << "\n";
        cout<<"     3. Toggle GCG/MSF format output     =  "
            << ((!userParameters->getOutputGCG()) ? "OFF" : "ON") << "\n";
        cout<<"     4. Toggle PHYLIP format output      =  "
            << ((!userParameters->getOutputPhylip()) ? "OFF" : "ON") << "\n";
        cout<<"     5. Toggle NEXUS format output       =  "
            << ((!userParameters->getOutputNexus()) ? "OFF" : "ON") << "\n";
        cout<<"     6. Toggle GDE format output         =  "
            << ((!userParameters->getOutputGde()) ? "OFF" : "ON") << "\n\n";
        cout<<"     7. Toggle GDE output case           =  "
            << ((!userParameters->getLowercase()) ? "UPPER" : "LOWER") << "\n";

        cout<<"     8. Toggle CLUSTALW sequence numbers =  "
            << ((!userParameters->getClSeqNumbers()) ? "OFF" : "ON") << "\n";
        cout<<"     9. Toggle output order              =  "
            << ((userParameters->getOutputOrder() == 0) ? "INPUT FILE" : "ALIGNED")
            <<"\n\n";

        cout<<"     0. Create alignment output file(s) now?\n\n";
        cout<<"     T. Toggle parameter output          = "
            << ((!userParameters->getSaveParameters()) ? "OFF" : "ON") << "\n";
        cout<<"     R. Toggle sequence range numbers =  "
            <<((!userParameters->getSeqRange()) ? "OFF" : "ON") << "\n\n";

        cout<<"     H. HELP\n\n\n";

        choice = utilityObject->getChoice(string("Enter number (or [RETURN] to exit)"));
        if (choice == '\n')
        {
            return ;
        }
        switch (toupper(choice))
        {
            case '1':
                userParameters->toggleOutputClustal();
                break;
            case '2':
                userParameters->toggleOutputNbrf();
                break;
            case '3':
                userParameters->toggleOutputGCG();
                break;
            case '4':
                userParameters->toggleOutputPhylip();
                break;
            case '5':
                userParameters->toggleOutputNexus();
                break;
            case '6':
                userParameters->toggleOutputGde();
                break;
            case '7':
                userParameters->toggleLowercase();
                break;
            case '8':
                userParameters->toggleClSeqNumbers();
                break;
            case '9':
                userParameters->toggleOutputOrder();
                break;
            case 'F':
                userParameters->toggleOutputFasta();
                break;
            case 'R':
                userParameters->toggleSeqRange();
                break;
            case '0':
                clustalObj->outputNow();
                break;
            case 'T':
                userParameters->toggleSaveParameters();
                break;
            case '?':
            case 'H':
                clustalObj->getHelp('5');
                break;
            default:
                cout<<"\n\nUnrecognised Command\n\n";
                break;
        }
    }
}
