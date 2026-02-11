alloc_register(GLboolean usedRegs[REG_ALLOCATE_MAX_PROGRAM_TEMPS])
{
   GLuint k;
   for (k = 0; k < REG_ALLOCATE_MAX_PROGRAM_TEMPS; k++) {
      if (!usedRegs[k]) {
         usedRegs[k] = GL_TRUE;
         return k;
      }
   }
   return -1;
}
