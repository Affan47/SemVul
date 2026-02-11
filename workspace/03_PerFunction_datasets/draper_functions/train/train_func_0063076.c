main (int argc, char *argv[])
{
  long digits = 100;
  while (argc >= 3) {
        if (!strcmp(argv[1],"-n")) {
            digits = atol(argv[2]);
            argc -= 2; argv += 2;
            continue;
        }
        break;
    }
    if (argc < 1)
        return(1);

  cl_LF c1;
  long l = digits;
  cout << "\nCalculating exp1 to " << l << " decimals" << endl;
  { CL_TIMING;
    const_exp1 (c1, l);
  }
  { CL_TIMING;
    cout << "@" << endl;
    cout << c1 << endl;
    cout << "@" << endl;
  }
  return(0);
}
