DeleteEnsemble(clientData)
    ClientData clientData;
{
    Ensemble* ensData = (Ensemble*)clientData;


    while (ensData->numParts > 0) {
        DeleteEnsemblePart(ensData->parts[0]);
    }
    ckfree((char*)ensData->parts);
    ckfree((char*)ensData);
}
