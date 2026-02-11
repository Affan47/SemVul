clusteringAlgorithmMenu()
{
    string currentAlgorithm = "";
    cout<<"****** CLUSTERING ALGORITHM MENU ******\n\n\n";
    while (true)
    {
        if(userParameters->getClusterAlgorithm() == NJ)
        {
            currentAlgorithm = "Neighbour Joining";
        }
        else
        {
            currentAlgorithm = "UPGMA";
        }
        lin1 = "";
        cout<< "\n\n\n";
        cout<<" ****** Clustering Algorithms ******\n\n\n";
        cout<<"     1. Neighbour Joining \n";
        cout<<"     2. UPGMA \n";
        cout << "-- Current algorithm is "<< currentAlgorithm << " --\n\n\n";


        choice = utilityObject->getChoice(string("Enter number (or [RETURN] to exit)"));
        if (choice == '\n')
        {
            return ;
        }
        switch (toupper(choice))
        {
            case '1':
                userParameters->setClusterAlgorithm(NJ);
                break;
            case '2':
                userParameters->setClusterAlgorithm(UPGMA);
                break;
            default:
                cout<< "\n\nUnrecognised Command\n\n";
                break;
        }
    }
}
