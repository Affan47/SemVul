convert_xml_child(HA_Message * msg, xmlNode * xml)
{
    int orig = 0;
    int rc = BZ_OK;
    unsigned int len = 0;

    char *buffer = NULL;
    char *compressed = NULL;
    const char *name = NULL;

    name = (const char *)xml->name;
    buffer = dump_xml_unformatted(xml);
    orig = strlen(buffer);
    if (orig < CRM_BZ2_THRESHOLD) {
        ha_msg_add(msg, name, buffer);
        goto done;
    }

    len = (orig * 1.1) + 600;

    compressed = malloc(len);
    rc = BZ2_bzBuffToBuffCompress(compressed, &len, buffer, orig, CRM_BZ2_BLOCKS, 0, CRM_BZ2_WORK);

    if (rc != BZ_OK) {
        crm_err("Compression failed: %d", rc);
        free(compressed);
        convert_xml_message_struct(msg, xml, name);
        goto done;
    }

    free(buffer);
    buffer = compressed;
    crm_trace("Compression details: %d -> %d", orig, len);
    ha_msg_addbin(msg, name, buffer, len);
  done:
    free(buffer);

#  if 0
    {
        unsigned int used = orig;
        char *uncompressed = NULL;

        crm_debug("Trying to decompress %d bytes", len);
        uncompressed = calloc(1, orig);
        rc = BZ2_bzBuffToBuffDecompress(uncompressed, &used, compressed, len, 1, 0);
        CRM_CHECK(rc == BZ_OK,;
            );
        CRM_CHECK(used == orig,;
            );
        crm_debug("rc=%d, used=%d", rc, used);
        if (rc != BZ_OK) {
            crm_exit(DAEMON_RESPAWN_STOP);
        }
        crm_debug("Original %s, decompressed %s", buffer, uncompressed);
        free(uncompressed);
    }
#  endif
}
