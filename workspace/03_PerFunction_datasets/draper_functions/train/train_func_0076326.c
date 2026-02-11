threadTestKill() {
    pthread_mutex_lock(&t_terminate_mutex);
    if (terminate_flag == true) {

        pthread_mutex_unlock(&t_terminate_mutex);
        return true;
    }
    pthread_mutex_unlock(&t_terminate_mutex);
    return false;
}
