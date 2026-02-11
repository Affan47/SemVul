openFilesForTreeFromAlignment(clustalw::OutputFile* clustalFile,
    clustalw::OutputFile* phylipFile, clustalw::OutputFile* distFile, clustalw::OutputFile* nexusFile, clustalw::OutputFile* pimFile,
                            clustalw::TreeNames* treeNames, string* path)
{
    if (clustalw::userParameters->getOutputTreeClustal())
    {
        if(!clustalFile || !clustalFile->openFile(&(treeNames->clustalName),
                                  "\nEnter name for CLUSTAL    tree output file  ",
                                  path, "nj", "Phylogenetic tree"))
        {
            return false;
        }
    }

    if (clustalw::userParameters->getOutputTreePhylip())
    {
        if(!phylipFile || !phylipFile->openFile(&(treeNames->phylipName),
                             "\nEnter name for PHYLIP     tree output file  ", path, "ph",
                             "Phylogenetic tree"))
        {
            return false;
        }
    }

    if (clustalw::userParameters->getOutputTreeDistances())
    {
        if(!distFile || !distFile->openFile(&(treeNames->distName),
                               "\nEnter name for distance matrix output file  ",
                               path, "dst", "Distance matrix"))
        {
            return false;
        }
    }

    if (clustalw::userParameters->getOutputTreeNexus())
    {
        if(!nexusFile || !nexusFile->openFile(&(treeNames->nexusName),
                                "\nEnter name for NEXUS tree output file  ", path,
                                     "tre", "Nexus tree"))
        {
            return false;
        }
    }

    if (clustalw::userParameters->getOutputPim())
    {
        if(!pimFile || !pimFile->openFile(&(treeNames->pimName),
                            "\nEnter name for % Identity matrix output file  ", path, "pim",
                            "perc identity"))
        {
            return false;
        }
    }
    return true;
}
