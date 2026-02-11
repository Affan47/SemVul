popState(GameState *who)
{
    removeState(who);

    if (!m_states.empty()) {
        checkStack();
    }
    else {
        MessagerAgent::agent()->forwardNewMsg(
                new SimpleMsg(Name::APP_NAME, "quit"));
    }
}
