is_fortran (void)
{
   unsigned int lang = get_lang_number ();

   return (lang == N_SO_FORTRAN) || (lang == N_SO_FORTRAN90);
}
