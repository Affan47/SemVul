is_numeric(char * string) {


  int num_period = 0;
  int i;
  int good = 0;


  for (i = 0; i < strlen(string); i++) {
    good = 0;
    if (string[i] >= 48 && string[i] <= 57) {
      good = 1;
    }

    if (string[i] == 46) {
      num_period++;
      good = 1;

      if (num_period > 1) {
        good = 0;
      }
    }

    if (string[i] == 45 && i == 0) {
      good = 1;
    }
    if (!good) {
      return 0;
    }
  }
  return 1;
}
