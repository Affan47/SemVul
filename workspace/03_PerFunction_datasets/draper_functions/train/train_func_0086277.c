removeFadeAnimation(const QModelIndex &index)
{
    QTimeLine *timeLine = m_timeLineMap.value(index, 0);
    m_timeLineMap.remove(index);
    m_timeLineInverseMap.remove(timeLine);
}
