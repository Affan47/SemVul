texturesMess (int argc, t_atom*argv) {
  if(!argc) {
    error("no textures specified!");
    return;
  }
  n=0;
  if(textures) delete [] textures;
  textures = new GLuint[argc];
  while(argc--){
    if(argv->a_type == A_FLOAT)textures[n++] = static_cast<GLuint>(atom_getint(argv));
    argv++;
  }
  setModified();
}
