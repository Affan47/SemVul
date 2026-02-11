mark(box& cube,FXint label,FXuchar map[33][33][33]){
  register FXint r,g,b;
  for(r=cube.r0+1; r<=cube.r1; ++r){
    for(g=cube.g0+1; g<=cube.g1; ++g){
      for(b=cube.b0+1; b<=cube.b1; ++b){
        map[r][g][b]=label;
        }
      }
    }
  }
