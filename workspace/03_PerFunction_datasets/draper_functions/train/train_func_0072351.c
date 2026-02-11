pdf_object_key(const gx_device_pdf * pdev, gs_id object_id, byte key[16])
{
    gs_md5_state_t md5;
    gs_md5_byte_t zero[2] = {0, 0}, t;
    int KeySize = pdev->KeyLength / 8;

    gs_md5_init(&md5);
    gs_md5_append(&md5, pdev->EncryptionKey, KeySize);
    t = (byte)(object_id >>  0);  gs_md5_append(&md5, &t, 1);
    t = (byte)(object_id >>  8);  gs_md5_append(&md5, &t, 1);
    t = (byte)(object_id >> 16);  gs_md5_append(&md5, &t, 1);
    gs_md5_append(&md5, zero, 2);
    gs_md5_finish(&md5, key);
    return min(KeySize + 5, 16);
}
