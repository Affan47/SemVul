ClearError(void) {
  int e = ERR_get_error();
  while(e != 0) {
    e = ERR_get_error();
  }
}

}
