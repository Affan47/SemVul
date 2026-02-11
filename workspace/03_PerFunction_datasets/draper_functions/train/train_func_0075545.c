registration(void) {
    Glib::Mutex::Lock lock(lock_);
    CondExit cond(cond_exited_);
    if ( infosys_type == "ISIS" ) {
        sendRegistrationToISIS();
    } else if ( infosys_type == "EMIREG" ) {
        sendRegistrationToEMIREG();
    }
}
