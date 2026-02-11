bangMess(void){
  unsigned int i;
  t_float*vertL=m_vertices;
  t_float*vertR=m_vertices+m_length;

  post("x\ty\tz\t\tx\ty\tz");
  for(i=0; i<m_length; i++) {
    post("%f\t%f\t%f\t\t%f\t%f\t%f",
         vertL[i*3+0],
         vertL[i*3+1],
         vertL[i*3+2],

         vertR[i*3+0],
         vertR[i*3+1],
         vertR[i*3+2]);
  }
}
