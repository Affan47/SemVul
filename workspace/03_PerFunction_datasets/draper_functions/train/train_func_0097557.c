print_rsa_pkey (gnutls_datum_t * m, gnutls_datum_t * e, gnutls_datum_t * d,
                gnutls_datum_t * p, gnutls_datum_t * q, gnutls_datum_t * u,
                gnutls_datum_t * exp1, gnutls_datum_t * exp2)
{
  fprintf (outfile, "modulus:");
  print_hex_datum (m);
  fprintf (outfile, "public exponent:");
  print_hex_datum (e);
  if (d)
    {
      fprintf (outfile, "private exponent:");
      print_hex_datum (d);
      fprintf (outfile, "prime1:");
      print_hex_datum (p);
      fprintf (outfile, "prime2:");
      print_hex_datum (q);
      fprintf (outfile, "coefficient:");
      print_hex_datum (u);
      if (exp1 && exp2)
        {
          fprintf (outfile, "exp1:");
          print_hex_datum (exp1);
          fprintf (outfile, "exp2:");
          print_hex_datum (exp2);
        }
    }
}
