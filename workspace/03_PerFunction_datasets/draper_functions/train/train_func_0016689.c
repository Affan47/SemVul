luS(enum usage_level ul, const char *command)
{
    int is_my_command = (command && 0 == strcmp(command, "S"));
    if (ul == usage_all || !command || is_my_command)
    FPS "%-15s Make a certificate and add to database\n",
        "-S");
    if (ul == usage_selected && !is_my_command)
        return;
    FPS "%-20s Specify the nickname of the cert\n",
        "   -n key-name");
    FPS "%-20s Specify the subject name (using RFC1485)\n",
        "   -s subject");
    FPS "%-20s The nickname of the issuer cert\n",
        "   -c issuer-name");
    FPS "%-20s Set the certificate trust attributes (see -A above)\n",
        "   -t trustargs");
#ifdef NSS_ENABLE_ECC
    FPS "%-20s Type of key pair to generate (\"dsa\", \"ec\", \"rsa\" (default))\n",
#else
    FPS "%-20s Type of key pair to generate (\"dsa\", \"rsa\" (default))\n",
#endif
        "   -k key-type-or-id");
    FPS "%-20s Name of token in which to generate key (default is internal)\n",
        "   -h token-name");
    FPS "%-20s Key size in bits, RSA keys only (min %d, max %d, default %d)\n",
        "   -g key-size", MIN_KEY_BITS, MAX_KEY_BITS, DEFAULT_KEY_BITS);
    FPS "%-20s Name of file containing PQG parameters (dsa only)\n",
        "   -q pqgfile");
#ifdef NSS_ENABLE_ECC
    FPS "%-20s Elliptic curve name (ec only)\n",
        "   -q curve-name");
    FPS "%-20s See the \"-G\" option for a full list of supported names.\n",
        "");
#endif
    FPS "%-20s Self sign\n",
        "   -x");
    FPS "%-20s Cert serial number\n",
        "   -m serial-number");
    FPS "%-20s Time Warp\n",
        "   -w warp-months");
    FPS "%-20s Months valid (default is 3)\n",
        "   -v months-valid");
    FPS "%-20s Specify the password file\n",
        "   -f pwfile");
    FPS "%-20s Cert database directory (default is ~/.netscape)\n",
        "   -d certdir");
    FPS "%-20s Cert & Key database prefix\n",
        "   -P dbprefix");
    FPS "%-20s Specify the contact phone number (\"123-456-7890\")\n",
        "   -p phone");
    FPS "%-20s Create key usage extension\n",
        "   -1 ");
    FPS "%-20s Create basic constraint extension\n",
        "   -2 ");
    FPS "%-20s Create authority key ID extension\n",
        "   -3 ");
    FPS "%-20s Create crl distribution point extension\n",
        "   -4 ");
    FPS "%-20s Create netscape cert type extension\n",
        "   -5 ");
    FPS "%-20s Create extended key usage extension\n",
        "   -6 ");
    FPS "%-20s Create an email subject alt name extension\n",
        "   -7 emailAddrs ");
    FPS "%-20s Create a DNS subject alt name extension\n",
        "   -8 DNS-names");
    FPS "%-20s Create an Authority Information Access extension\n",
        "   --extAIA ");
    FPS "%-20s Create a Subject Information Access extension\n",
        "   --extSIA ");
    FPS "%-20s Create a Certificate Policies extension\n",
        "   --extCP ");
    FPS "%-20s Create a Policy Mappings extension\n",
        "   --extPM ");
    FPS "%-20s Create a Policy Constraints extension\n",
        "   --extPC ");
    FPS "%-20s Create an Inhibit Any Policy extension\n",
        "   --extIA ");
    FPS "%-20s Create a subject key ID extension\n",
        "   --extSKID ");
    FPS "%-20s \n",
        "   See -G for available key flag options");
    FPS "%-20s Create a name constraints extension\n",
        "   --extNC ");
    FPS "\n");
}
