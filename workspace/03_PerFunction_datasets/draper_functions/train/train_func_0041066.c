operator<<(ostream & f,const ArrayOfaType & a)
   {
     for (int i=0;i<a.n;i++)
       f <<  (i ? ", " : " ") << *a.t[i];
       if (a.ellipse ) f << "... ";
       else            f << " ";
      return f;}
