intersect( const Ray& r , Hit& h , float tmin ) {
  bool result = false;
  for( unsigned int i = 0 ; i < t.size() ; i++){
    Triangle triangle(v[t[i][0]],
                      v[t[i][1]],v[t[i][2]],material);
    for(int jj=0;jj<3;jj++){
      triangle.normals[jj] = n[t[i][jj]];

    }
    if(texCoord.size()>0){
      for(int jj=0;jj<3;jj++){
        triangle.texCoords[jj] = texCoord[t[i].texID[jj]];
      }
      triangle.hasTex=true;
    }
    result |= triangle.intersect( r , h , tmin);
  }
  return result;
}
