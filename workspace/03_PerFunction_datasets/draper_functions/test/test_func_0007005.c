bc_set_class_version(JVM_CLASS *class, int major, int minor)
{
  if(!class) {
    BAD_ARG();
    return -1;
  }

  class->major_version = (u2)major;
  class->minor_version = (u2)minor;

  if((unsigned int)class->major_version != major)
    debug_err("Warning: possible truncation in bc_set_class_version.\n");

  if((unsigned int)class->minor_version != minor)
    debug_err("Warning: possible truncation in bc_set_class_version.\n");

  return 0;
}
