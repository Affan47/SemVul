check_x931_derived_key (int what)
{
  static struct {
    const char *param;
    const char *expected_d;
  } testtable[] = {
    {
      "(genkey\n"
      "  (rsa\n"
      "    (nbits 4:1024)\n"
      "    (rsa-use-e 1:3)\n"
      "    (derive-parms\n"
      "      (Xp1 #1A1916DDB29B4EB7EB6732E128#)\n"
      "      (Xp2 #192E8AAC41C576C822D93EA433#)\n"
      "      (Xp  #D8CD81F035EC57EFE822955149D3BFF70C53520D\n"
      "            769D6D76646C7A792E16EBD89FE6FC5B605A6493\n"
      "            39DFC925A86A4C6D150B71B9EEA02D68885F5009\n"
      "            B98BD984#)\n"
      "      (Xq1 #1A5CF72EE770DE50CB09ACCEA9#)\n"
      "      (Xq2 #134E4CAA16D2350A21D775C404#)\n"
      "      (Xq  #CC1092495D867E64065DEE3E7955F2EBC7D47A2D\n"
      "            7C9953388F97DDDC3E1CA19C35CA659EDC2FC325\n"
      "            6D29C2627479C086A699A49C4C9CEE7EF7BD1B34\n"
      "            321DE34A#))))\n",
      "1CCDA20BCFFB8D517EE9666866621B11822C7950D55F4BB5BEE37989A7D173"
      "12E326718BE0D79546EAAE87A56623B919B1715FFBD7F16028FC4007741961"
      "C88C5D7B4DAAAC8D36A98C9EFBB26C8A4A0E6BC15B358E528A1AC9D0F042BE"
      "B93BCA16B541B33F80C933A3B769285C462ED5677BFE89DF07BED5C127FD13"
      "241D3C4B"
    },

    {
      "(genkey\n"
      "  (rsa\n"
      "    (nbits 4:1536)\n"
      "    (rsa-use-e 1:3)\n"
      "    (derive-parms\n"
      "      (Xp1 #18272558B61316348297EACA74#)\n"
      "      (Xp2 #1E970E8C6C97CEF91F05B0FA80#)\n"
      "      (Xp  #F7E943C7EF2169E930DCF23FE389EF7507EE8265\n"
      "            0D42F4A0D3A3CEFABE367999BB30EE680B2FE064\n"
      "            60F707F46005F8AA7CBFCDDC4814BBE7F0F8BC09\n"
      "            318C8E51A48D134296E40D0BBDD282DCCBDDEE1D\n"
      "            EC86F0B1C96EAFF5CDA70F9AEB6EE31E#)\n"
      "      (Xq1 #11FDDA6E8128DC1629F75192BA#)\n"
      "      (Xq2 #18AB178ECA907D72472F65E480#)\n"
      "      (Xq  #C47560011412D6E13E3E7D007B5C05DBF5FF0D0F\n"
      "            CFF1FA2070D16C7ABA93EDFB35D8700567E5913D\n"
      "            B734E3FBD15862EBC59FA0425DFA131E549136E8\n"
      "            E52397A8ABE4705EC4877D4F82C4AAC651B33DA6\n"
      "            EA14B9D5F2A263DC65626E4D6CEAC767#))))\n",
      "1FB56069985F18C4519694FB71055721A01F14422DC901C35B03A64D4A5BD1"
      "259D573305F5B056AC931B82EDB084E39A0FD1D1A86CC5B147A264F7EF4EB2"
      "0ED1E7FAAE5CAE4C30D5328B7F74C3CAA72C88B70DED8EDE207B8629DA2383"
      "B78C3CE1CA3F9F218D78C938B35763AF2A8714664CC57F5CECE2413841F5E9"
      "EDEC43B728E25A41BF3E1EF8D9EEE163286C9F8BF0F219D3B322C3E4B0389C"
      "2E8BB28DC04C47DA2BF38823731266D2CF6CC3FC181738157624EF051874D0"
      "BBCCB9F65C83"


    },

    {
      "(genkey\n"
      "  (rsa\n"
      "    (nbits 4:1024)\n"
      "    (rsa-use-e 1:3)\n"
      "    (derive-parms\n"
      "      (Xp1 #1ed3d6368e101dab9124c92ac8#)\n"
      "      (Xp2 #16e5457b8844967ce83cab8c11#)\n"
      "      (Xp  #b79f2c2493b4b76f329903d7555b7f5f06aaa5ea\n"
      "            ab262da1dcda8194720672a4e02229a0c71f60ae\n"
      "            c4f0d2ed8d49ef583ca7d5eeea907c10801c302a\n"
      "            cab44595#)\n"
      "      (Xq1 #1a5d9e3fa34fb479bedea412f6#)\n"
      "      (Xq2 #1f9cca85f185341516d92e82fd#)\n"
      "      (Xq  #c8387fd38fa33ddcea6a9de1b2d55410663502db\n"
      "            c225655a9310cceac9f4cf1bce653ec916d45788\n"
      "            f8113c46bc0fa42bf5e8d0c41120c1612e2ea8bb\n"
      "            2f389eda#))))\n",
      "17ef7ad4fd96011b62d76dfb2261b4b3270ca8e07bc501be954f8719ef586b"
      "f237e8f693dd16c23e7adecc40279dc6877c62ab541df5849883a5254fccfd"
      "4072a657b7f4663953930346febd6bbd82f9a499038402cbf97fd5f068083a"
      "c81ad0335c4aab0da19cfebe060a1bac7482738efafea078e21df785e56ea0"
      "dc7e8feb"
    },

    {
      "(genkey\n"
      "  (rsa\n"
      "    (nbits 4:1536)\n"
      "    (rsa-use-e 1:3)\n"
      "    (derive-parms\n"
      "      (Xp1 #1e64c1af460dff8842c22b64d0#)\n"
      "      (Xp2 #1e948edcedba84039c81f2ac0c#)\n"
      "      (Xp  #c8c67df894c882045ede26a9008ab09ea0672077\n"
      "            d7bc71d412511cd93981ddde8f91b967da404056\n"
      "            c39f105f7f239abdaff92923859920f6299e82b9\n"
      "            5bd5b8c959948f4a034d81613d6235a3953b49ce\n"
      "            26974eb7bb1f14843841281b363b9cdb#)\n"
      "      (Xq1 #1f3df0f017ddd05611a97b6adb#)\n"
      "      (Xq2 #143edd7b22d828913abf24ca4d#)\n"
      "      (Xq  #f15147d0e7c04a1e3f37adde802cdc610999bf7a\n"
      "            b0088434aaeda0c0ab3910b14d2ce56cb66bffd9\n"
      "            7552195fae8b061077e03920814d8b9cfb5a3958\n"
      "            b3a82c2a7fc97e55db543948d3396289245336ec\n"
      "            9e3cb308cc655aebd766340da8921383#))))\n",
      "1f8b19f3f5f2ac9fc599f110cad403dcd9bdf5f7f00fb2790e78e820398184"
      "1f3fb3dd230fb223d898f45719d9b2d3525587ff2b8bcc7425e40550a5b536"
      "1c8e9c1d26e83fbd9c33c64029c0e878b829d55def12912b73d94fd758c461"
      "0f473e230c41b5e4c86e27c5a5029d82c811c88525d0269b95bd2ff272994a"
      "dbd80f2c2ecf69065feb8abd8b445b9c6d306b1585d7d3d7576d49842bc7e2"
      "8b4a2f88f4a47e71c3edd35fdf83f547ea5c2b532975c551ed5268f748b2c4"
      "2ccf8a84835b"
    }
  };
  gpg_error_t err;
  gcry_sexp_t key_spec, key, pub_key, sec_key;
  gcry_mpi_t d_expected, d_have;

  if (what < 0 && what >= sizeof testtable)
    die ("invalid WHAT value\n");

  err = gcry_sexp_new (&key_spec, testtable[what].param, 0, 1);
  if (err)
    die ("error creating S-expression [%d]: %s\n", what, gpg_strerror (err));

  err = gcry_pk_genkey (&key, key_spec);
  gcry_sexp_release (key_spec);
  if (err)
    die ("error generating RSA key [%d]: %s\n", what, gpg_strerror (err));

  pub_key = gcry_sexp_find_token (key, "public-key", 0);
  if (!pub_key)
    die ("public part missing in key [%d]\n", what);

  sec_key = gcry_sexp_find_token (key, "private-key", 0);
  if (!sec_key)
    die ("private part missing in key [%d]\n", what);

  err = gcry_mpi_scan
    (&d_expected, GCRYMPI_FMT_HEX, testtable[what].expected_d, 0, NULL);
  if (err)
    die ("error converting string [%d]\n", what);

  if (verbose > 1)
    show_sexp ("generated key:\n", key);

  d_have = key_param_from_sexp (sec_key, "rsa", "d");
  if (!d_have)
    die ("parameter d not found in RSA secret key [%d]\n", what);
  if (gcry_mpi_cmp (d_expected, d_have))
    {
      show_sexp (NULL, sec_key);
      die ("parameter d does match expected value [%d]\n", what);
    }
  gcry_mpi_release (d_expected);
  gcry_mpi_release (d_have);

  gcry_sexp_release (key);
  gcry_sexp_release (pub_key);
  gcry_sexp_release (sec_key);
}
