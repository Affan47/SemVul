InitVOMSAttribute(void) {
    #define idpkix                "1.3.6.1.5.5.7"
    #define idpkcs9               "1.2.840.113549.1.9"
    #define idpe                  idpkix ".1"
    #define idce                  "2.5.29"
    #define idaca                 idpkix ".10"
    #define idat                  "2.5.4"
    #define idpeacauditIdentity   idpe ".4"
    #define idcetargetInformation idce ".55"
    #define idceauthKeyIdentifier idce ".35"
    #define idceauthInfoAccess    idpe ".1"
    #define idcecRLDistPoints     idce ".31"
    #define idcenoRevAvail        idce ".56"
    #define idceTargets           idce ".55"
    #define idacaauthentInfo      idaca ".1"
    #define idacaaccessIdentity   idaca ".2"
    #define idacachargIdentity    idaca ".3"
    #define idacagroup            idaca ".4"
    #define idatclearance         "2.5.1.5.5"
    #define voms                  "1.3.6.1.4.1.8005.100.100.1"
    #define incfile               "1.3.6.1.4.1.8005.100.100.2"
    #define vo                    "1.3.6.1.4.1.8005.100.100.3"
    #define idatcap               "1.3.6.1.4.1.8005.100.100.4"

    #define attribs            "1.3.6.1.4.1.8005.100.100.11"
    #define acseq                 "1.3.6.1.4.1.8005.100.100.5"
    #define order                 "1.3.6.1.4.1.8005.100.100.6"
    #define certseq               "1.3.6.1.4.1.8005.100.100.10"
    #define email                 idpkcs9 ".1"

    #define OBJC(c,n) OBJ_create(c,n,#c)

    X509V3_EXT_METHOD *vomsattribute_x509v3_ext_meth;


    OpenSSLInit();

    static Glib::Mutex lock_;
    static bool done = false;

    Glib::Mutex::Lock lock(lock_);
    if (done) return;


    OBJC(idatcap,"idatcap");

    OBJC(attribs,"attributes");
    OBJC(idcenoRevAvail, "idcenoRevAvail");
    OBJC(idceauthKeyIdentifier, "authKeyId");
    OBJC(idceTargets, "idceTargets");
    OBJC(acseq, "acseq");
    OBJC(order, "order");
    OBJC(voms, "voms");
    OBJC(incfile, "incfile");
    OBJC(vo, "vo");
    OBJC(certseq, "certseq");

    vomsattribute_x509v3_ext_meth = VOMSAttribute_auth_x509v3_ext_meth();
    if (vomsattribute_x509v3_ext_meth) {
      vomsattribute_x509v3_ext_meth->ext_nid = OBJ_txt2nid("authKeyId");
      X509V3_EXT_add(vomsattribute_x509v3_ext_meth);
    }

    vomsattribute_x509v3_ext_meth = VOMSAttribute_avail_x509v3_ext_meth();
    if (vomsattribute_x509v3_ext_meth) {
      vomsattribute_x509v3_ext_meth->ext_nid = OBJ_txt2nid("idcenoRevAvail");
      X509V3_EXT_add(vomsattribute_x509v3_ext_meth);
    }

    vomsattribute_x509v3_ext_meth = VOMSAttribute_targets_x509v3_ext_meth();
    if (vomsattribute_x509v3_ext_meth) {
      vomsattribute_x509v3_ext_meth->ext_nid = OBJ_txt2nid("idceTargets");
      X509V3_EXT_add(vomsattribute_x509v3_ext_meth);
    }

    vomsattribute_x509v3_ext_meth = VOMSAttribute_acseq_x509v3_ext_meth();
    if (vomsattribute_x509v3_ext_meth) {
      vomsattribute_x509v3_ext_meth->ext_nid = OBJ_txt2nid("acseq");
      X509V3_EXT_add(vomsattribute_x509v3_ext_meth);
    }

    vomsattribute_x509v3_ext_meth = VOMSAttribute_certseq_x509v3_ext_meth();
    if (vomsattribute_x509v3_ext_meth) {
      vomsattribute_x509v3_ext_meth->ext_nid = OBJ_txt2nid("certseq");
      X509V3_EXT_add(vomsattribute_x509v3_ext_meth);
    }

    vomsattribute_x509v3_ext_meth = VOMSAttribute_attribs_x509v3_ext_meth();
    if (vomsattribute_x509v3_ext_meth) {
      vomsattribute_x509v3_ext_meth->ext_nid = OBJ_txt2nid("attributes");
      X509V3_EXT_add(vomsattribute_x509v3_ext_meth);
    }

    if(!PersistentLibraryInit("modcredential")) {
      CredentialLogger.msg(WARNING, "Failed to lock arccredential library in memory");
    };
    done=true;

  }
