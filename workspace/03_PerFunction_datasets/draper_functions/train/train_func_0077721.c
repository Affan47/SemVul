read_spec(spec, part)


char spec[];
struct vstring* part;
{
  char* in;
  int i, j;
  int stackptr;
  char* stack[10];
  char lastch = 0;

  stackptr = 0;
  in = spec;
  while (((*in >= 'A') && (*in <= 'Z')) || (*in == '(') || (*in == '.') ||
         (*in == ')') || (*in == '+') || (*in == '-') ||
         ((*in >= '0') && (*in <= '9'))) {
    if (*in == '.') {
      in = in + 1;
    };


    if ((*in >= 'A') && (*in <= 'Z')) {
      char_out(part, *in);
      lastch = *in;
      in = in + 1;
    };
    if (*in == '(') {
      if (stackptr < 10) {
        stack[stackptr] = part->st + strlen(part->st);
        stackptr = stackptr + 1;
      } else {
        event_error("nesting too deep in part specification");
      };
      in = in + 1;
    };
    if (*in == ')') {
      in = in + 1;
      if (stackptr > 0) {
        int repeats;
        char* start;
        char* stop;

        if ((*in >= '0') && (*in <= '9')) {
          repeats = readnump(&in);
        } else {
          repeats = 1;
        };
        stackptr = stackptr - 1;
        start = stack[stackptr];
        stop = part->st + strlen(part->st);
        for (i=1; i<repeats; i++) {
          for (j=0; j<((int) (stop-start)); j++) {
            char_out(part, *(start+j));
          };
        };
      } else {
        event_error("Too many )'s in part specification");
      };
    };
    if ((*in >= '0') && (*in <= '9')) {
      int repeats;

      repeats = readnump(&in);
      if (part->len > 0) {
        for (i = 1; i<repeats; i++) {
          char_out(part, lastch);
        };
      } else {
        event_error("No part to repeat in part specification");
      };
    };
  };
  if (stackptr != 0) {
    event_error("Too many ('s in part specification");
  };
}
