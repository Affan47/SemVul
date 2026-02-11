jar_parse_sig(JAR *jar, const char *path, char *raw_manifest,
	      long length)
{
    JAR_Signer *signer;
    int status = JAR_ERR_ORDER;

    if (length <= 128) {

	return JAR_ERR_SIG;
    }


    if (jar->globalmeta == NULL)
	return JAR_ERR_ORDER;


    if (path) {
	char *owner;
	owner = jar_basename(path);

	if (owner == NULL)
	    return JAR_ERR_MEMORY;

	signer = jar_get_signer(jar, owner);
	PORT_Free(owner);
    } else
	signer = jar_get_signer(jar, "*");

    if (signer == NULL)
	return JAR_ERR_ORDER;


    if (length > 64000) {

	return JAR_ERR_SIG;
    }


    status = jar_parse_digital_signature(raw_manifest, signer, length, jar);

    return status;
}
