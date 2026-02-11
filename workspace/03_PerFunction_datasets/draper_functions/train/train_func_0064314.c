is_mostly_ascii(struct http_response* res) {
  u32 i, total, printable = 0;

  if (res->doc_type) return (res->doc_type == 2);

  total = (res->pay_len > 128) ? 128 : res->pay_len;

  if (!total) { res->doc_type = 2; return 1; }

  for (i=0;i<total;i++)
    if ((res->payload[i] >= 0x20 && res->payload[i] <= 0x7f)
        || (res->payload[i] && strchr("\t\r\n", res->payload[i])))
      printable++;

  if (printable * 100 / total < 90) {
    DEBUG("* looks like binary data (print = %u, total = %u)\n",
          printable, total);
    res->doc_type = 1;
    return 1;
  }

  DEBUG("* looks like text file (print = %u, total = %u)\n",
        printable, total);

  res->doc_type = 2;
  return 1;

}
