mark()
{


    bool useQuestion = Settings::useQuestionMarks();

    switch(m_state)
    {
        case KMinesState::Released:
            m_state = KMinesState::Flagged;
            break;
        case KMinesState::Flagged:
            m_state = useQuestion ? KMinesState::Questioned : KMinesState::Released;
            break;
        case KMinesState::Questioned:
            m_state = KMinesState::Released;
            break;
        default:

            break;
    }
    updatePixmap();
}
