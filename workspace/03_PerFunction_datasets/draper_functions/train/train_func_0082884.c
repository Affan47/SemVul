user_pop(void) {

    if (user_push_counter == stack_level) {
        this->pop();
    } else {
        new AP_ERR("AP_main::user_pop()","No user pop possible");
    }
    return;
}
