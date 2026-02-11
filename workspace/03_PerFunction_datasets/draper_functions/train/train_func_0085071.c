parseTime()
{
    m_time = KGlobal::locale()->readTime(q->lineEdit()->text());
}
