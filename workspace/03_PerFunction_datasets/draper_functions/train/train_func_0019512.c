operator[](unsigned bitPosition) const {
  return (maskBit(bitPosition) &
          (isSingleWord() ?  VAL : pVal[whichWord(bitPosition)])) != 0;
}
