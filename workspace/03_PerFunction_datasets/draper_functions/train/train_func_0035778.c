import_encrypted(const Filename *filename, int type, char **comment)
{
    if (type == SSH_KEYTYPE_OPENSSH) {

	*comment = dupstr(filename_to_str(filename));
	return openssh_encrypted(filename);
    }
    if (type == SSH_KEYTYPE_SSHCOM) {
	return sshcom_encrypted(filename, comment);
    }
    return 0;
}
