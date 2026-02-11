setT2Resend(int32_t counter) {
    if (counter < 0 || counter > 10)
        stateEngine->setT2Resend(counter);
}
