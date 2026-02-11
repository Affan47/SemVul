query_bool(const char *mes, ...)
{

 va_list ap;
 va_start(ap, mes);
 char buff[6000];
 vsprintf(buff, mes, ap);
 va_end(ap);

 std::string full_line = buff;
 full_line += " (Y/N/Q)";

 print_line(full_line.c_str());
 char ret;
 do
  ret = getch();
 while (ret != 'y' && ret != 'Y' && ret != 'n' && ret != 'N' && ret != 'q' &&
        ret != 'Q');
 return (ret == 'y' || ret == 'Y');
}
