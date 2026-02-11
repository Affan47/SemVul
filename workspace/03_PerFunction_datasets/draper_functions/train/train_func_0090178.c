removeService(InfoRegister* reg) {
    Glib::Mutex::Lock lock(lock_);
    for(std::list<Register_Info_Type>::iterator r = reg_.begin();
                                           r!=reg_.end();++r) {
        if(reg == r->p_register) {
            if ( infosys_type == "ISIS" ) {
                sendDeleteToISIS(r);
            } else if ( infosys_type == "EMIREG" ) {
                sendDeleteToEMIREG(r);
            }
            return true;
        };
    };
    logger_.msg(VERBOSE, "Unregistred Service can not be removed.");
    return false;
}
