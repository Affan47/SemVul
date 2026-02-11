removeEventListener(KasumiWordEventListener *listener){
    vector<KasumiWordEventListener*>::iterator i;
    KasumiWordEventListener *p;

    for(i=EventListeners.begin();i!=EventListeners.end();i++){
	p = *i;
	if(p == listener){
	    EventListeners.erase(i);
	    return;
	}
    }
}
