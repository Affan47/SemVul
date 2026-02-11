lcd_draw_thread(void *lcdlist){

    g15daemon_t *masterlist = (g15daemon_t*)(lcdlist);

    lcd_t *displaying = masterlist->tail->lcd;
    memset(displaying->buf,0,1024);
    static int prev_state=0;
    g15daemon_sleep(2);

    while (!leaving) {

        g15daemon_wait_refresh();

        pthread_mutex_lock(&lcdlist_mutex);
        displaying = masterlist->current->lcd;


        g15daemon_log(LOG_DEBUG,"Updating LCD");
        uf_write_buf_to_g15(displaying);
        g15daemon_log(LOG_DEBUG,"LCD Update Complete");

        if(prev_state!=displaying->backlight_state && set_backlight!=0) {
              prev_state=displaying->backlight_state;
              pthread_mutex_lock(&g15lib_mutex);
              setLCDBrightness(displaying->backlight_state);
              usleep(5);
              setLCDBrightness(displaying->backlight_state);
              setKBBrightness(displaying->backlight_state);
              pthread_mutex_unlock(&g15lib_mutex);
        }

        if(displaying->state_changed){
            pthread_mutex_lock(&g15lib_mutex);
            setLCDContrast(displaying->contrast_state);
            if(displaying->masterlist->remote_keyhandler_sock==0)
              setLEDs(displaying->mkey_state);
            pthread_mutex_unlock(&g15lib_mutex);
            displaying->state_changed = 0;
        }

        pthread_mutex_unlock(&lcdlist_mutex);
    }
    return NULL;
}
