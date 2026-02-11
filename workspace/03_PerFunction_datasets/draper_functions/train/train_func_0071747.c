deleteIntElement(std::vector<int> * source, int index) {
    int i,n;
    std::vector<int> temp(source->size()-1);

    n=0;
    for (i=0; i<source->size(); i++) if (i != index) {
      temp[n]=(*source)[i];
      n++;
    };
    source->resize(source->size()-1);
    for (i=0; i<source->size(); i++) (*source)[i]=temp[i];
  }
