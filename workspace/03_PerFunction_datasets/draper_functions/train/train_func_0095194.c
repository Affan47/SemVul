parse_fixup_v380_npc_restr (sc_bool notinsameroom, sc_int npc,
                            const sc_char *failmessage)
{

  if (npc > 0)
    {
      sc_int var2;

      if (npc == 1)
        {

          var2 = notinsameroom ? 3 : 2;
          parse_fixup_v380_restr (3, 3, 0, var2, 0, failmessage);
          return;
        }


      var2 = notinsameroom ? 1 : 0;
      parse_fixup_v380_restr (3, 3, 0, var2, npc, failmessage);
    }
}
