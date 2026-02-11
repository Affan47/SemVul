load(FXStream& store){
  FXuchar hadvertices,hadcolors,hadnormals,hadtextures;
  FXGLShape::load(store);
  store >> vertexNumber;
  store >> hadvertices >> hadcolors >> hadnormals >> hadtextures;
  if(hadvertices){ FXMALLOC(&vertexBuffer,FXfloat,3*vertexNumber); store.load(vertexBuffer,3*vertexNumber); }
  if(hadcolors){ FXMALLOC(&colorBuffer,FXfloat,4*vertexNumber); store.load(colorBuffer,4*vertexNumber); }
  if(hadnormals){ FXMALLOC(&normalBuffer,FXfloat,3*vertexNumber); store.load(normalBuffer,3*vertexNumber); }
  if(hadtextures){ FXMALLOC(&textureBuffer,FXfloat,2*vertexNumber); store.load(textureBuffer,2*vertexNumber); }
  }
