su_StoreSDLEvent(const SDL_Event &tEvent){
    if (next_in!=current_out && !input_get){

        tEvents[currentIn]=tEvent;
        times[currentIn]=Time();
        increase(currentIn);
        next_in=currentIn;
        increase(next_in);
        return false;
    }
    return true;
}
