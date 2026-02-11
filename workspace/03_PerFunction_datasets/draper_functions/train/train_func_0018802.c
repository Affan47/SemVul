calcHeatFrict()
{
  double heat_frict = 0.0 ;
  double ratio,heati,heatj ;

   if(getSlipping()) {

     heat_frict = dot(m_Ffric, m_ds) ;

     if(m_p1->getDo2dCalculations()){
        ratio = m_p1->getRad()*m_p1->getRad()/(m_p1->getRad()*m_p1->getRad()+m_p2->getRad()*m_p2->getRad() );
     }else {
        ratio = m_p1->getRad()*m_p1->getRad()*m_p1->getRad()/(m_p1->getRad()*m_p1->getRad()*m_p1->getRad()+m_p2->getRad()*m_p2->getRad()*m_p2->getRad() );
     }

     heati =  heat_frict*ratio ;
     heatj =  heat_frict*(1.0-ratio) ;
     m_p1->applyHeatFrict(heati) ;
     m_p2->applyHeatFrict(heatj) ;
   }
}
