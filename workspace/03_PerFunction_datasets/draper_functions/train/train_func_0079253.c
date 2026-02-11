aes_decrypt(std::string in, std::string key){
    in = decode(in);
    if(key.length() < 32){
        key.append(32 - key.length(), '\0');
    }

    unsigned char *output = new unsigned char[in.length()];

    AES_KEY *aesKey = new AES_KEY;
    AES_set_decrypt_key((unsigned char*)key.c_str(), 256, aesKey);

    AES_cbc_encrypt((unsigned char*)in.c_str(), output, in.length(), aesKey, (unsigned char*)key.substr(16).c_str(), AES_DECRYPT);

    std::string ret((char*) output);

    delete output;
    delete aesKey;

    return ret;
}
