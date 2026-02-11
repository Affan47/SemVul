PrefixMatch(const xstring& id) const
{
   int bytes=prefix_bits/8;
   int bits=prefix_bits%8;
   unsigned mask=~((1<<(8-bits))-1);
   if(bytes>0 && memcmp(prefix.get(),id.get(),bytes))
      return false;
   if(bits>0 && (prefix[bytes]&mask)!=(id[bytes]&mask))
      return false;
   return true;
}
