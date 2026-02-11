DoOnIdle(wxIdleEvent& evt) {

    if ( Idle() )
        evt.RequestMore();
    else
        SetIdle(false);
}
