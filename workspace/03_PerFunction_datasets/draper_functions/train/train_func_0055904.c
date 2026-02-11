output_keylength_table (void)
{
  const int max_column = 15;
  int slot = 0;
  int column = 0;
  const char *indent = option[GLOBAL] ? "" : "  ";
  List_Node *temp;

  if (!option[DUP] && !option[SWITCH])
    {
      ACE_OS::printf ("\n%sstatic %sunsigned %s lengthtable[] =\n%s%s{\n    ",
                      indent,
                      option[CONSTANT] ? "const " : "",
                      max_key_len <= ((int) UCHAR_MAX) ? "char" : (max_key_len <= ((int) USHRT_MAX) ? "short" : "long"),
                      indent,
                      indent);

      for (temp = head; temp; temp = temp->next, slot++)
        {

          if (slot < temp->hash_value)
            for ( ; slot < temp->hash_value; slot++)
              ACE_OS::printf ("%3d,%s", 0, ++column % (max_column - 1) ? "" : "\n    ");

          ACE_OS::printf ("%3d,%s", temp->length, ++column % (max_column - 1 ) ? "" : "\n    ");
        }

      ACE_OS::printf ("\n%s%s};\n",
                      indent,
                      indent);
    }
}
