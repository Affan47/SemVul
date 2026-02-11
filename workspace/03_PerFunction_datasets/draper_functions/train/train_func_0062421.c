sort(){
  vector< pair<float,int> > fvals(nfib);
  ColumnVector ftmp(nfib),thtmp(nfib),phtmp(nfib);
  ftmp=m_f;thtmp=m_th;phtmp=m_ph;
  for(int i=1;i<=nfib;i++){
    pair<float,int> p(m_f(i),i);
    fvals[i-1] = p;
  }
  std::sort(fvals.begin(),fvals.end());
  for(int i=1,ii=nfib-1;ii>=0;i++,ii--){
    m_f(i)  = ftmp(fvals[ii].second);
    m_th(i) = thtmp(fvals[ii].second);
    m_ph(i) = phtmp(fvals[ii].second);
  }
}
