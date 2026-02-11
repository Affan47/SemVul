typeSampler( TIntermTyped *node, TBasicType samp )
{
   TIntermSymbol *symNode = node->getAsSymbolNode();

   if ( !symNode)
   {


      TIntermBinary *biNode = node->getAsBinaryNode();

      if ( biNode )
      {
         switch (biNode->getOp())
         {
         case EOpIndexDirect:
         case EOpIndexIndirect:
            infoSink.info << "Warning: " << node->getLine() <<  ": typing of sampler arrays presently unsupported\n";
            break;

         case EOpIndexDirectStruct:
            infoSink.info << "Warning: " << node->getLine() <<  ": typing of samplers as struct members presently unsupported\n";
            break;
         default:
            break;
         }
      }
      else
      {
         infoSink.info << "Warning: " << node->getLine() <<  ": unexpected expression type for sampler, cannot type\n";
      }
      abort = false;
   }
   else
   {

      abort = true;
      id = symNode->getId();
      sampType = samp;
   }
}
