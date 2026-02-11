Clp_idiot(Clp_Simplex * model, int tryhard)
{
     ClpSimplex *clp = model->model_;
     Idiot info(*clp);
     int numberpass = tryhard >> 3;
     int lightweight = tryhard & 7;
     info.setLightweight(lightweight);
     info.crash(numberpass, clp->messageHandler(), clp->messagesPointer(), false);
}
