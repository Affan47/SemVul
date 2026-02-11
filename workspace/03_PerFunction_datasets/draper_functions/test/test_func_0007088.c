ReportProgress(Object *who, const EventObject & event)
{
  ProgressEvent pe;
  StartEvent se;

  if ( typeid( event ) == typeid( pe ) )
    {

    m_AccumulatedProgress = m_BaseAccumulatedProgress;


    FilterRecordVector::iterator it;
    for ( it = m_FilterRecord.begin(); it != m_FilterRecord.end(); ++it )
      {
      m_AccumulatedProgress += it->Filter->GetProgress() * it->Weight;
      }


    m_MiniPipelineFilter->UpdateProgress(m_AccumulatedProgress);


    if ( m_MiniPipelineFilter->GetAbortGenerateData() )
      {

      FilterRecordVector::iterator fit;
      for ( fit = m_FilterRecord.begin(); fit != m_FilterRecord.end(); ++fit )
        {
        if ( who == fit->Filter )
          {
          fit->Filter->AbortGenerateDataOn();
          }
        }
      }
    }
  else if ( typeid( event ) == typeid( se ) )
  {


    FilterRecordVector::iterator it;
    for ( it = m_FilterRecord.begin(); it != m_FilterRecord.end(); ++it )
    {
      if( who == it->Filter )
      {


        m_BaseAccumulatedProgress += it->Filter->GetProgress() * it->Weight;
      }
    }
  }
}
