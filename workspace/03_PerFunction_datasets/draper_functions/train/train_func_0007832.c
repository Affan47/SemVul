put(DBT *key, const DBT *data, uint32_t flag) {
  if (flag && flag != R_NOOVERWRITE) {
    throw std::runtime_error("illegal flag");
  }
  return (hash_access(flag == R_NOOVERWRITE ? HASH_PUTNEW : HASH_PUT, key,
                      const_cast<DBT *>(data)));
}
