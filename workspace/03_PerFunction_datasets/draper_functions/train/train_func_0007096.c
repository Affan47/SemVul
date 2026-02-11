console_write(struct inode *ip, char *buf, int n)
{
  int i;

  iunlock(ip);
  acquire(&console_lock);
  for(i = 0; i < n; i++)
    cons_putc(buf[i] & 0xff);
  release(&console_lock);
  ilock(ip);

  return n;
}
