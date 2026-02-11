setLesson(Lesson* lesson)
{
    if (lesson != m_lesson)
    {
        if (m_lesson)
        {
            m_lesson->disconnect(this);
        }

        m_lesson = lesson;

        if (m_lesson)
        {
            connect(m_lesson, SIGNAL(titleChanged()), SLOT(reset()));
            connect(m_lesson, SIGNAL(textChanged()), SLOT(reset()));
        }

        reset();

        emit lessonChanged();
    }
}
