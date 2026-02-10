addInfRefreshTime()
{


    SPtr<TClntCfgIface> ptr;
    firstIface();
    while ( ptr = getIface() ) {
        if (!ptr->stateless())
            return false;
    }

    return true;
}
