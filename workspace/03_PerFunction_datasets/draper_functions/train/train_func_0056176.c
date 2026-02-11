getPropertyOrValueEnum(int32_t bytesTrieOffset, const char *alias) {
    BytesTrie trie(bytesTries+bytesTrieOffset);
    if(containsName(trie, alias)) {
        return trie.getValue();
    } else {
        return UCHAR_INVALID_CODE;
    }
}
